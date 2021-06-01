using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

public class SendMatrixJson

{
    public static void serializeMatrix(int[,] matrix)
    {
        string json = JsonConvert.SerializeObject(matrix, Formatting.Indented);
        SingletonInt.Instance.client.SendMsg("{ \"algorithm\" : 0}");
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
