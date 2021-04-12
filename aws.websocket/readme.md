# required tools
    $ npm install aws-cli -g
    $ npm install serverless -g

# for deployment
$ serverless deploy

```
/* connect */
{
  "requestContext": {
    "connectionId": "abc123"
  }
}
```

```
/* registerPairCode */
{
  "requestContext": {
    "connectionId": "abc123"
  },
  "body": "{\"data\": { \"pairCode\": \"4444\", \"partyType\": \"web\" }}"
}
```

```
/* sendMessage */
{
  "requestContext": {
    "connectionId": "abc123"
  },
  "body": "{ \"data\": { \"pairCode\": \"4444\", \"targetPartyType\": \"web\", \"message\": { \"heartBeat\": \"beat\" } } }"
}
```

```
/* disconnect */
{
  "requestContext": {
    "connectionId": "abc123"
  }
}
```

# messages from web browser
```
/* web browser party (party type) register a pair code */
{ "action": "registerPairCode", "data": { "pairCode": "2344", "partyType": "web" } }
```

```
/* web browser party (type) send a message telling it has established communication through the provide pair code */
{ "action": "sendMessage", "data": { "pairCode": "2344", "targetPartyType": "device", "message": { "heartBeat": "beat" } } }
```
