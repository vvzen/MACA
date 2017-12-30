var Twitter = require('twitter');
var fs = require('fs');
var path = require('path');

var auth_params = JSON.parse(fs.readFileSync(path.join(__filename, "..", "auth.json"), { "encoding": "utf8" }));

console.log(auth_params.consumer_key);

var client = new Twitter({
    consumer_key: auth_params.consumer_key,
    consumer_secret: auth_params.consumer_secret,
    access_token_key: auth_params.access_token_key,
    access_token_secret: auth_params.access_token_secret
});

var query_params = {
    q: "generative art",
    result_type: "popular",
    count: 100
}

client.get("search/tweets", query_params, function(error, tweets, response) {

    console.log(`Found ${tweets.statuses.length} statuses`);

    tweets["statuses"].forEach(element => {
        console.log(JSON.stringify(element.text) + "\n");
    });
});
