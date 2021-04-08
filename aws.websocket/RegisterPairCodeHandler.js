'use strict'

const AWS = require('aws-sdk');
const dynamo = new AWS.DynamoDB.DocumentClient();

const WEB_SOCKET_MESSAGES_TABLE = process.env.WEB_SOCKET_MESSAGES_TABLE;

const PAIRING_CODE_REGISTERED_RESPONSE = {
    statusCode: 201,
    body: 'Pairing Code Registered'
}

module.exports.handle = (event, context, callback) => {
    const connectionId = event.requestContext.connectionId;

    const body = JSON.parse(event.body);
    const {pairCode, partyType} = body.data;

    persistConnectionDetails(pairCode, partyType, connectionId)
        .then(() => {
            callback(null, PAIRING_CODE_REGISTERED_RESPONSE);
        })
        .catch((err) => {
            callback(failedResponse(500, JSON.stringify(err)));
        });
}

const persistConnectionDetails = (pairCode, partyType, connectionId) => {
    const params = {
        TableName: WEB_SOCKET_MESSAGES_TABLE,
        Key: {
            connectionId: connectionId
        },
        UpdateExpression: ' SET pairCode = :paramPairCode, partyType = :paramPartyType ',
        ExpressionAttributeValues: {
            ':paramPairCode': pairCode,
            ':paramPartyType': partyType
        }
    };

    return dynamo
        .update(params)
        .promise();
}

const failedResponse = (statusCode, error) => (
    {
        statusCode,
        body: error
    }
);