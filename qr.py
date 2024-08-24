# Generates a QR code
# https://github.com/lincolnloop/python-qrcode

import os
import qrcode

img = qrcode.make("https://youtube.be/xvFZjo5PgGO")

img.save("qr.png", "PNG")

os.system("open qr.png")
