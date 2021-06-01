using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;

public class SendMatrixJson

{
    public static void serializeMatrix(int[,] matrix)
    {
        string json = JsonConvert.SerializeObject(matrix, Formatting.Indented);
        SingletonInt.Instance.client.SendMsg("0");
        string msg = "{ \"matrix:\"" + json + "}";
        SingletonInt.Instance.client.SendMsg(msg);
        int[,] product = JsonConvert.DeserializeObject<int[,]>(SingletonInt.Instance.client.ReceiveMsg());
        DrawPredictiveLine.DrawLine(product);

    }


}
