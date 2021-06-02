using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

public class SendMatrixJson

{
    public static void serializeMatrix(int[,] matrix)
    {

        if (SingletonInt.Instance.isPlayer) { SingletonInt.Instance.client.SendMsg("{ \"algorithm\" : 0}"); }
        else { SingletonInt.Instance.client.SendMsg("{ \"algorithm\" : 1}"); }
        
        string json = JsonConvert.SerializeObject(matrix, Formatting.Indented);
        
        string msg = "{ \"matrix\" :" + json + "}";
        SingletonInt.Instance.client.SendMsg(msg);
        Debug.Log("se envió json");
        var jObj = JObject.Parse(SingletonInt.Instance.client.ReceiveMsg());
        int[,] product = jObj["matrix"].ToObject<int[,]>();
        Debug.Log("Se recibió respuesta");
        Debug.Log(product);
        DrawPredictiveLine.DrawLine(product);

    }


}
