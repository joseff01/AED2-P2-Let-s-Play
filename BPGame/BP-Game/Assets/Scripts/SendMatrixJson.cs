using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

public class SendMatrixJson

{   /**
    *
    * @brief  serializeMatrix recive matriz y la envia al servidor
    * @param matrix recive la matriz que se va a enviar
    * */
    public static void serializeMatrix(int[,] matrix)
    {
        
        if (SingletonInt.Instance.isPlayer) { SingletonInt.Instance.client.SendMsg("{ \"algorithm\" : 0}"); }
        else { SingletonInt.Instance.client.SendMsg("{ \"algorithm\" : 1}"); }
        
        string json = JsonConvert.SerializeObject(matrix, Formatting.Indented);
        
        string msg = "{ \"matrix\" :" + json + "}";
        SingletonInt.Instance.client.SendMsg(msg);  // Se envio Json
      
        var jObj = JObject.Parse(SingletonInt.Instance.client.ReceiveMsg()); //Se recivio respuesta 
        int[,] product = jObj["matrix"].ToObject<int[,]>();

        DrawPredictiveLine.DrawLine(product);
        
        

    }


}
