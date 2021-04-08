'use strict'

const AWS = require('aws-sdk');
const dynamo = new AWS.DynamoDB.DocumentClient();

const WEB_SOCKET_MESSAGES_TABLE = process.env.WEB_SOCKET_MESSAGES_TABLE;

const CONNECTION_CREATED_RESPONSE = {
  statusCode: 201,
  body: 'Connection Stablished'
}

module.exports.handle = (event, context, callback) => {
  const connectionId = event.requestContext.connectionId;

  persistConnectionId(connectionId)
      .then(() => {
          callback(null, CONNECTION_CREATED_RESPONSE);
      })
      .catch((err) => {
          callback(failedResponse(500, JSON.stringify(err)));
      });
}

const persistConnectionId = (connectionId) => {
  const params = {
      TableName: WEB_SOCKET_MESSAGES_TABLE,
      Item: {
          connectionId: connectionId
      }
  };

  return dynamo
      .put(params)
      .promise();
}

const failedResponse = (statusCode, error) => (
  {
      statusCode,
      body: error
  }
);