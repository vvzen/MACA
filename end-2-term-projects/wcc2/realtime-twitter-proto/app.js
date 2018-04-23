const Twit = require('twit')
const fs = require('fs');
const osc = require('osc-min');
const dgram = require("dgram");

try {
    const twitter_auth = JSON.parse(fs.readFileSync('auth.json', 'utf-8'));
}
catch (e){
    console.error("ERROR:\nYou need to provide a auth.json file.\nSee the readme on how to get one.\nSee you soon.\n");
    process.exit();
}

const T = new Twit({
  consumer_key:         twitter_auth.consumer_key,
  consumer_secret:      twitter_auth.consumer_secret,
  access_token:         twitter_auth.access_token,
  access_token_secret:  twitter_auth.access_token_secret,
  timeout_ms:           60*1000,  // optional HTTP request timeout to apply to all requests.
});

// setup osc
const udp = dgram.createSocket("udp4");
const osc_port = 9000;
function send_osc_message(city, tweet, nation, lon, lat){
    let buffer;
    buffer = osc.toBuffer({
        address: "/twitter-app",
        args: [
            {
                type: "string",
                value: city
            },
            {
                type: "string",
                value: tweet
            },
            {
                type: "string",
                value: nation
            },
            {
                type: "float",
                value: lon
            },
            {
                type: "float",
                value: lat
            }
        ]
    });
    return udp.send(buffer, 0, buffer.length, osc_port, "localhost");
}

const world_capitals = JSON.parse(fs.readFileSync('world_cities_countries.geojson'));

const target_cities_for_streaming = [];

let cities_count = 0;
world_capitals.features.forEach(function(feature){

    // console.log(feature);

    try {
        
        let name = feature.properties.NAME_EN;
        
        let nation = feature.properties["SOV0NAME"];
        
        if (name && nation){
            cities_count++;
            console.log(name);
            name = name
            .toLowerCase()
            .replace(/ /g, '_')
            .replace(/,/g, '')
            .replace(/\'/, '');

            name = `#${name}`;

            target_cities_for_streaming.push(
                {
                    name : name,
                    nation: nation
                }
            );
        }
    }
    catch (e){
        console.log(e.message);
    }
});

console.log(`streaming on ${cities_count} cities`);

// start streaming
// console.log(target_cities_for_streaming);

const stream = T.stream('statuses/filter', {
    track: target_cities_for_streaming.map((c) => { return c.name; })
});

fs.writeFile("nations.json", JSON.stringify(target_cities_for_streaming.map((c) => { return c.nation; })), (err) => {

});

console.log('started listening to tweets');
stream.on('tweet', function (tweet) {

    let current_city;
    let current_nation;
    let tweet_text;

    // check if tweet is a retweet
    if (/^RT/g.test(tweet.text)){
        try {
            // console.log(`\nretweeted status: ${tweet.retweeted_status.extended_tweet.full_text}`);
            tweet_text = tweet.retweeted_status.extended_tweet.full_text;
        }
        catch (err) {
            // console.log(`\ntweet text: ${tweet.text}`);
            tweet_text = tweet.text;
        }
    }
    else {
        try {
            tweet_text = tweet.extended_tweet.full_text;
        }
        catch (err){
            tweet_text = tweet.text;
        }
    }

    // check if we've parsed the json correctly
    if (!tweet_text){
        console.log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        fs.writeFile("missing_text_tweet.json", JSON.stringify(tweet), () => {
            
        });
    }
    else {
        // find which city is the tweet about
        for (let city of target_cities_for_streaming){
            
            let city_name = city.name;
            
            var re = new RegExp(city_name.toLowerCase(), "g");
            
            if (tweet_text.toLowerCase().match(re)){
                current_nation = city.nation;
                console.log(`\ncurrent tweet nation: ${current_nation}`);
                console.log(`\ncurrent tweet city: ${city_name}`);
                current_city = city_name.replace('#', '');
            }

        }
        let hashtags = [];
        tweet.entities.hashtags.forEach(function(hashtag){
            hashtags.push(hashtag.text);
        });
        let lon, lat;
        if (tweet.coordinates){
            // esample of santiago: { type: 'Point', coordinates: [ -71.2509046, -29.9032854 ]};
            lon = tweet.coordinates.coordinates[0];
            lat = tweet.coordinates.coordinates[1];
        }
        else {
            lon = -1;
            lat = -1;
        }
        if (current_city) send_osc_message(current_city, hashtags.join(" #"), current_nation, lon, lat);
        
    }
    console.log(tweet_text);
    
    // log coordinates if present
    if (tweet.coordinates !== null){
        console.log(`tweet location:`);
        console.log(tweet.coordinates);
    }
    // console.log('hashtags: ');
    // tweet.entities.hashtags.forEach(function(hashtag){
    //     console.log(`\t${hashtag.text}`);
    // });
    // console.log(tweet);

});