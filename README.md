# Halvarsson_Client
This is the client side of a theoretical school-project building a restaurant menu on a android application using the QT-toolkit. (made with qtcreator)
The client-side can be build to an android.apk and can run on a android device.


The client connects to a <a href="https://github.com/Morindhal/Halvarsson_server">server</a> hosted on a PC (linux or windows) through websockets and recieves update-events from the server as well as sends events to the server that the client would wish sent to all other clients to recieve.

This project is unfinished and unlikely to ever be continued.


Currently the client side can handle events to/from the server updating the info from all tables and has a timer on said table telling you how old the oldest order on that table is in seconds.
The UI would need to be re-built to a smarter layout, more adapted to an android device, if it is to ever be finished.
