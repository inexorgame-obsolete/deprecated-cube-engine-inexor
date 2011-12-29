#!/usr/bin/env python

from threading import Thread
import socket
import time
from time import gmtime, strftime
import os
import sys
import string

class masterserver(object):

    settings = {
        "host": "sauerbomber.org",
        "port": 28787,
        "log": "master.log"
    }
    
    proxy = {
        "host": "sauerbraten.org",
        "port": 28787
    }
    
    servers = []
    
    shutdown = False
    logfile = None
    serv = None
    updatesecs = 60

    def log(self, text):
        if self.logfile == None:
            if os.path.exists(self.settings["log"]):
                self.logfile = open(self.settings["log"], "a")
            else:
                self.logfile = open(self.settings["log"], "w")
        self.logfile.write("\n" + time.strftime("[%a %m/%d/%Y %H:%M:%S] ") + text)
        self.logfile.flush()

    def getserversfromproxy(self):
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            try:
                s.connect((self.proxy["host"], self.proxy["port"]))
                s.send('list\n')
                data = ""
                while True:
                    bucket=s.recv(512)
                    if not bucket:
                        break
                    else:
                        data += bucket
                s.close()
                return data
            except socket.error, msg:
                self.log("PROXY: error in connecting to masterserver %s:%s" %(self.proxy["host"], self.proxy["port"]))
                s.close()
                s = None
        except socket.error, msg:
            self.log("PROXY: error in creating socket")
            s = None
        return 'echo "error connecting remote masterserver %s:%s"' %(proxy_hostname, proxy_port)

    def getlocalservers(self):
        s_str = ""
        for server in self.servers:
            if s_str == "":
                s_str = "addserver %s %s\n" %(server["ip"], server["port"])
            else:
                s_str = "%saddserver %s %s\n" %(s_str, server["ip"], server["port"])
        return s_str

    def register(self, ip, port):
        server = {
            "ip": ip,
            "port": port
        }
        already = False
        for s in self.servers:
            if s["ip"] == server["ip"] and s["port"] == server["port"]:
                already = True
        if not already:
            self.servers.append(server)
        return True

    def unregister(self, ip, port):
        server = {
            "ip": ip,
            "port": port
        }
        already = False
        for s in self.servers:
            if s["ip"] == server["ip"] and s["port"] == server["port"]:
                self.servers.remove(s)

    def acceptclient(self, infos):
        if self.shutdown:
            return
        self.log("accepted a connection: " + str(infos[1]))
        con = infos[0]
        cid = str(infos[1][1])
        ip = str(infos[1][0])
        data = con.recv(4096)
        if data == "list\n":
            serverstr = "%s%s" %(self.getlocalservers(), self.getserversfromproxy())
            con.send(serverstr)
            #self.log("=== successfully sent server list ===")
            #self.log(serverstr)
            #self.log("=== successfully sent server list ===")
        else:
            if data[0:7] == "regserv":
                port = data[8:].replace("\n","").replace("\r","")
                if self.register(ip, port):
                    self.log("successfully registered server %s %s" %(ip, port))
                    con.send("succreg\n")
                    i = 0
                    while i < self.updatesecs and not self.shutdown:
                        time.sleep(1)
                else:
                    self.log("failed to register server %s %s" %(ip, port))
                    con.send("failreg\n")
            else:
                self.log("client wanted something unknown: %s" %(data))
        self.log("request done")
        # con.send("");
        con.close()

    def initsocket(self):
        i = 0
        while i < 5:
            i = i + 1
            try:
                self.log("starting...")
                self.serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                self.serv.bind((self.settings["host"], self.settings["port"]))
                #self.serv.setsockopt(socket.IPPROTO_IP, socket.IP_HDRINCL, 1)
                #self.serv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
                self.serv.listen(1)
                return True
            except:
                self.log("ERROR socket initialization failed, retrying in 5 seconds")
                time.sleep(5)
        return False

    def main(self):
        if not self.initsocket():
            self.log("could not start masterserver: hostname or port error")
            print "could not start masterserver: hostname or port error"
            return
        else:
            self.log("port binding succeeded...")
            print "waiting for clients ..."
        while True:
            try:
                infos = self.serv.accept()
                try:
                    temp_thread = Thread(target=self.acceptclient, args=(infos,))
                    temp_thread.start()
                except:
                    pass
            except:
                self.log("shutdown...")
                self.shutdown = True
                self.logfile.close()
                return
        
if __name__ == '__main__':
    ms = masterserver()
    ms.main()
