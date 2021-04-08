'use strict'

module.exports.defaultHandler = (event, context, callback) => {
    callback(null, failedResponse(404, 'No event found'))
}

const failedResponse = (statusCode, error) => (
    {
        statusCode,
        body: error
    }
);