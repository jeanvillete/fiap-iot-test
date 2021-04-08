'use strict'

const AWS = require('aws-sdk');
const dynamo = new AWS.DynamoDB.DocumentClient();

const WEB_SOCKET_MESSAGES_TABLE = process.env.WEB_SOCKET_MESSAGES_TABLE;

const SUCCESSFULL_RESPONSE = {
    statusCode: 200,
    body: 'Disconnected'
};

module.exports.handle = (event, context, callback) => {
    const connectionId = event.requestContext.connectionId;
    
    deleteConnection(connectionId)
        .then(() => {
            callback(null, SUCCESSFULL_RESPONSE)
        })
        .catch((err) => {
            callback(failedResponse(500, JSON.stringify(err)))
        })
}

const deleteConnection = (connectionId) => {
    const params = {
        TableName: WEB_SOCKET_MESSAGES_TABLE,
        Key: {
            connectionId: connectionId
        }
    }

    return dynamo
        .delete(params)
        .promise()
}

const failedResponse = (statusCode, error) => (
    {
        statusCode,
        body: error
    }
);