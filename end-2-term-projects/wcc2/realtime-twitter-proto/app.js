const Twit = require('twit')
const fs = require('fs');
const osc = require('osc-min');
const dgram = require("dgram");

const twitter_auth = JSON.parse(fs.readFileSync('auth.json', 'utf-8'));

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
function send_osc_message(city){
    let buffer;
    buffer = osc.toBuffer({
        address: "/twitter-app",
        args: [{
            type: "string",
            value: city
        }]
    });
    return udp.send(buffer, 0, buffer.length, osc_port, "localhost");
}

const uk_cities = JSON.parse(fs.readFileSync('uk_cities_clipped.geojson'));

const target_cities_for_streaming = [];
uk_cities.features.forEach(function(city){

    let name = city.properties.name
        .toLowerCase()
        .replace(/ /g, '')
        .replace(/\'/, '');
    
    name = `#${name}`;

    target_cities_for_streaming.push(name);
        
});

// start streaming
console.log(target_cities_for_streaming);

const stream = T.stream('statuses/filter', {track: target_cities_for_streaming});

stream.on('tweet', function (tweet) {

    let current_city;
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
            var re = new RegExp(city.toLowerCase(), "g");
            if (tweet_text.toLowerCase().match(re)){
                console.log(`\ncurrent tweet city: ${city}`);
                current_city = city.replace('#', '');
            }
        }
        if (current_city) send_osc_message(current_city);
    }
    console.log(tweet_text);
    
    // log coordinates if present
    if (tweet.coordinates !== null){
        console.log(`tweet location:`);
        console.log(tweet.coordinates);
    }
    console.log('hashtags: ');
    tweet.entities.hashtags.forEach(function(hashtag){
        console.log(`\t${hashtag.text}`);
    });
    // console.log(tweet);

});