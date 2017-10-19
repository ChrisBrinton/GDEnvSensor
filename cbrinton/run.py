#!/usr/bin/python

import os
from eve import Eve

if 'PORT' in os.environ:
	port = int(os.environ.get('PORT'))
	# use '0.0.0.0' to ensure your REST API is reachable from all your
	# networks (and not just the localhost
	host = '0.0.0.0'
else:
	port = 5000
	host = '0.0.0.0'

app = Eve()

if __name__ == '__main__':
	app.run(host=host, port=port)
