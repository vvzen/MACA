'use strict'

// A DEBUG file used to fix some issues with the polly module
/*
   first install the following node modules:
       npm install aws-sdk
       npm install stream
       npm install speaker
   if after running the sample, you get an error 'Illegal instruction: 4'
   then also do the following step, AFTER those above:
       npm install speaker --mpg123-backend=openal
   also sure that you have a file in the following location:
       ~/.aws/credentials (c:\users\USER_NAME\.aws\credentials on Windows)
   which contains your aws credentials in this form:
       [default]
       aws_access_key_id = YOUR_ACCESS_KEY_ID
       aws_secret_access_key = YOUR_SECRET_ACCESS_KEY
    when all set-up, run the sample like this:
       node polly.js
*/

// --- dependencies

const aws     = require ('aws-sdk');
const stream  = require ('stream');
const speaker = require ('speaker');

// --- constants

const DEFAULT_VOICE  = /* The lovely */ 'Amy';
const SPEAKER_CONFIG = { channels: 1, bitDepth: 16, sampleRate: 16000 };

// --- the polly class

function Polly (region)
{
    this._polly = new aws.Polly ({region: region});
    this._voice = DEFAULT_VOICE;

    this.voice = function (voice)  // see https://docs.aws.amazon.com/polly/latest/dg/voicelist.html
    {
        this._voice = voice;
    }

    this.say = function (speech, callback)
    {
        var utterance = { OutputFormat: 'pcm', VoiceId: this._voice, Text: speech };

        this._polly.synthesizeSpeech (utterance, (error, data) =>
        {
            if (!error && data && data.AudioStream instanceof Buffer)
            {
                var buffer = new stream.PassThrough ();
                var player = new speaker (SPEAKER_CONFIG);

                buffer.end (data.AudioStream);
                buffer.pipe (player);

                player.on ('finish', function ()
                {

		    console.log("finished!");
                    buffer.unpipe (player);
                    buffer.end ();
                    player.close ();

                    if (callback)
                    {
                        callback ();
                    }
                });
            }
        });
    }
}

// --- example usage

var polly = new Polly ('us-west-2');

console.log ();
console.log ('Ulysses by Sir Alfred Lord Tennyson');
console.log ();

polly.say ('We are not now that strength, which in old days moved Earth and heaven', function ()
{
    polly.voice ('Brian');

    polly.say ('That which we are we are. One equal temper of heroic hearts', function ()
    {
        polly.voice ('Emma');

        polly.say ('Made weak by time and fate, but strong in will', function ()
        {
            polly.voice ('Raveena');

            polly.say ('To strive, to seek, to find, and not to yield.');  // no callback here, as its optional
        });
    });
});
