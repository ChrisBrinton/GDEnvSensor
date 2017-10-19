MONGO_HOST = 'localhost'
MONGO_PORT = 27017

MONGO_DBNAME = 'gdtechdb_prod'

PAGINATION = 'true'
PAGINATION_LIMIT = 500
PAGINATION_DEFAULT = 100

X_DOMAINS = '*'

# Enable reads (GET), inserts (POST) and DELETE for resources/collections
# (if you omit this line, the API will default to ['GET'] and provide
# read-only access to the endpoint).
#RESOURCE_METHODS = ['GET', 'POST', 'DELETE']

# Enable reads (GET), edits (PATCH), replacements (PUT) and deletes of
# individual items  (defaults to read-only item access).
#ITEM_METHODS = ['GET', 'PATCH', 'PUT', 'DELETE']

Sensors = {
    # 'title' tag used in item links. Defaults to the resource title minus
    # the final, plural 's' (works fine in most cases but not for 'people')
    'item_title': 'Sensor',

    # by default the standard item entry point is defined as
    # '/people/<ObjectId>'. We leave it untouched, and we also enable an
    # additional read-only entry point. This way consumers can also perform
    # GET requests at '/people/<lastname>'.
    'additional_lookup': {
        'url': 'regex("[\w]+")',
        'field': 'gateway_id'
    },
    'additional_lookup': {
        'url': 'regex("[\w\w]+")',
        'field': 'gateway_id',
        'field': 'type'
    },

    # We choose to override global cache-control directives for this resource.
    'cache_control': 'max-age=10,must-revalidate',
    'cache_expires': 10,

    # most global settings can be overridden at resource level
    #'resource_methods': ['GET', 'POST'],
    'schema': {
        'model': {
            'type': 'string',
            },
        'gateway_id': {
            'type': 'string',
        },
        'node_id': {
            'type': 'integer',
        },
        'type': {
            'type': 'string',
        },
        'value': {
            'type': 'string',
        },
        'time': {
            'type': 'number',
        },
    }
}

DOMAIN = {
	'Sensors': Sensors,
}
