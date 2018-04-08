// This code is here to just document one way of achieving TTS
// on a raspberry pi or udoo or linux machine, using the say npm package.
// Beware that Amazon Polly is way better, but requires a good internet connection.
// It requires the festival package to be installed on your system.
// Further instructions can be found here: https://learn.adafruit.com/speech-synthesis-on-the-raspberry-pi/installing-the-festival-speech-package

const say = require('say');


let current_voice;
if (process.platform == "linux"){
    current_voice = "voice_default";
}
else {
    current_voice = "Alex";    
}

say.speak("Hello this is an audio test", current_voice, 1.0, (err) => {
                    
    if (err){
        console.log(err);
    }
});
