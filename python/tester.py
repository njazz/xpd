from puredatapy import *

import puredatapy as pd

from time import sleep

print(dir(pd))

s = pd.ServerSettings("default");
ls = pd.LocalServer(s);
proc = ls.create_process();

cnv = proc.create_canvas();

o1 = cnv.create_object("osc~ 261", 100, 100);
o2 = cnv.create_object("dac~", 100, 150);

# print(cnv.available_objects());
# print(cnv.objects().find_object(o1));

cnv.connect(o1,0,o2,0);
cnv.connect(o1,0,o2,1);

proc.dsp_switch(True);

# print(cnv.objects().get())

sleep(1) # Time in seconds.

cnv.disconnect(o1,0,o2,0);

sleep(1) # Time in seconds.

proc.dsp_switch(False);
