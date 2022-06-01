import os
import subprocess
import sys

sys.path.append("..")
path = os.getcwd() + '/CrSDK_v1.05.00_20211207a_Linux64PC/build/RemoteCli'
for i in range(10):
    # os.startfile(path)
    os.system(path)
# subprocess.call([opener, filename])
