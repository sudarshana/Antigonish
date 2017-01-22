from Tkinter import * #https://wiki.python.org/moin/TkInter

root = Tk () 
#root = The first Tk object. All Tkinter apps must have a root 

root.geometry ( "640x400+10+10" ) 
# Geomtery method = size and position of the window. Do not use * Use x.

myContainer = Frame ( root )
myContainer.pack ( side = TOP, expand = YES, fill = BOTH )

myLabel = Label ( myContainer, text = "Building things are fun" )
myLabel.pack ( side = TOP, expand = YES, fill = BOTH)

btn = Button ( root, text = "Yep!" )
btn.pack ()

root.mainloop ()
