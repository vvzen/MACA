const fs = require('fs');
const Twit = require('twit');
const say = require('say');

var listening_words = ["generative art", "art"];

var T = new Twit({
    consumer_key: "GwPXQ3ZKWraOIbphjOSIOU3Xf",
    consumer_secret: "OUgVdkKsJYKai7jdmecbzlVwX4XaqN9fTz4QDDDoJcieBqBfQ6",
    access_token: "973638431774560262-2kgZMwY9SeiOa59PRoQz2YrelsvTK2Z",
    access_token_secret: "yNyuV7yy2VGT60SyEkTM4bC2dUm5AIC7NSUFqLlAcM89O",
    timeout_ms: 60 * 1000, // optional HTTP request timeout to apply to all requests.
});

// Create a stream object that filters the public stream
var stream = T.stream("statuses/filter", {
    track: listening_words,
    language: "en"
});

console.log(`started streaming on ${listening_words.toString()}`);

say.stop();
say.speak("GO", "Alex");

// Start streaming
stream.on("tweet", function (tweet) {
    // console.log(tweet.text);

    // remove the https string from the text using a regex
    var text_cleaned = tweet.text.split(/https:\/\/\w+.co\/\w+/);

    if (text_cleaned.length > 0){
        
        //say.stop();
        stream.stop();

        say.speak(text_cleaned[0], "Alex", 1.0, (err) => {
            
            if (err){
                console.log(err);
            }

            stream.start();
        });
        console.log("heard a new tweet!");
    }
});