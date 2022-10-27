# https://github.com/FireHead90544/craiyon.py

import requests
import sys
from craiyon import Craiyon

generator = Craiyon() # Instantiates the api wrapper
result = generator.generate(sys.argv[1])
result.save_images()
