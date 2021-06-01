using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using UnityEngine;
public class BPClient
{
    // Client socket. 
    public Socket workSocket = null;
    // Received data string. 
    public StringBuilder sb = new StringBuilder();
    // Port no.
    public const int port = 5000;
    //Client socket
    Socket client;
    /**
     * Function that creates the conection to the C++ BPServer. It won't send anything, just make the conection
     */
    public void StartClient()
    {
        try
        {
            //Set localhost IP
            IPHostEntry ipHostInfo = Dns.GetHostEntry("localhost");
            IPAddress ipAddress = ipHostInfo.AddressList[0];
            IPEndPoint remoteEP = new IPEndPoint(ipAddress, port);
            // Create a TCP/IP socket. 
            client = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            client.Connect(remoteEP);

        }
        catch (System.Exception)
        {
            throw;
        }
    }
    /**
     * Function that sends a message to the C++ BPSrver
     * @param receivedString String that wants to be sent to the server
     */
    public void SendMsg(string receivedString)
    {
        Debug.Log("Enviando mensaje: ");
        Debug.Log(receivedString);
        byte[] msg = Encoding.ASCII.GetBytes(receivedString);
        client.Send(msg);
    }
    /**
     * Function that makes the client wait for a message sent by the server and returns said  message.
     * WARNING: If no messsage is sent back by the server immediately, the entire client will freeze until it does.
     * @return receivedString string received from the server
     */
    public string ReceiveMsg()
    {
        byte[] buffer = new byte[2048];
        int bytesRec = client.Receive(buffer);
        string receivedString = Encoding.ASCII.GetString(buffer, 0, bytesRec);
        return receivedString;
    }


}