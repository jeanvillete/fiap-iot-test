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
