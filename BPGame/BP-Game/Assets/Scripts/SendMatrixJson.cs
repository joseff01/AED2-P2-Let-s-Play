using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;

public class SendMatrixJson
{
    public static void serializeMatrix(int[,] matrix)
    {
        string json = JsonConvert.SerializeObject(matrix, Formatting.Indented);
    }

}
