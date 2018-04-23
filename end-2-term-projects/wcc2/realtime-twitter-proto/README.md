# README

IMPORTANT--> Use the **popup-installation** branch, which contains the latest changes.

Tested with node version v9.11.1, npm version 5.6.0.<br>
This small app sends OSC messages using [osc-min](https://github.com/russellmcc/node-osc-min).<br>
It streams tweets from twitter using [twit](https://github.com/ttezel/twit).

## Installation

You must have nodejs installed.
Node *(along with npm, its official package manager)* can be installed in 1 minute following [this official guide](https://nodejs.org/en/download/package-manager/).
Then, you simply:

1. Download this folder as a zip
2. ```cd``` into into it
3. type `npm install` in order to install all the dependencies
4. type `npm run app` to run this app.
5. If you didn't provide your own *auth.json* file, you will see an error.<br>
   See below to provide your own *auth credentials* to use the twitter api.

## Credentials

Auth credentials for twitter login can be simply obtained following [this guide](https://themepacific.com/how-to-generate-api-key-consumer-token-access-key-for-twitter-oauth/994/) or going to [this address](https://apps.twitter.com) to add a new twitter app and following the steps.

Those credentials should then be put inside a file called *auth.json*, with this structure:

```
{
    "consumer_key": "your consumer key..",
    "consumer_secret": "your consumer secret..",
    "access_token": "your access token..",
    "access_token_secret": "your access token secret.."
}
```
