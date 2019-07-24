//$Id$
/**
 * 
 */
package com.test;

import java.io.IOException;
import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

import javax.websocket.*;

import javax.websocket.Session;
import javax.websocket.server.ServerEndpoint;



/**
 * @author kamal157
 *
 */
@ServerEndpoint("/node")
public class WebSocket {

	private static Set<Session> peers = Collections.synchronizedSet(new HashSet<Session>());
	
    @OnOpen
    public void onOpen (Session peer) throws Exception {
    	peer.getBasicRemote().sendText("welcome");
        peers.add(peer);

    }

    @OnClose
    public void onClose (Session peer) {
        peers.remove(peer);
    }
    
    @OnMessage
    public void onMessage (String s,Session ses) throws Exception
    {
    	
    		peers.stream().filter(each -> !each.equals(ses))
    					 .forEach(each -> {
										try {
											each.getBasicRemote().sendText(s);
										} catch (IOException e) {
											// TODO Auto-generated catch block
											e.printStackTrace();
										}
						});
		
    }
   
		
		

	
}
