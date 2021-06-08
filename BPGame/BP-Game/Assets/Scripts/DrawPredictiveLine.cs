using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;

public class DrawPredictiveLine : MonoBehaviour
{
    private static BallClick bola  = null;
    private static LineRenderer lineRenderer = new GameObject("Line").AddComponent<LineRenderer>();

    public static void InstantiateLineRenderer()
    {
        //For creating line renderer object
        lineRenderer.startColor = Color.red;
        lineRenderer.endColor = Color.red;
        lineRenderer.startWidth = 0.05f;
        lineRenderer.endWidth = 0.05f;
        lineRenderer.useWorldSpace = true;

        DontDestroyOnLoad(lineRenderer);

    }

    public static void DrawLine(int[,] mapMatrix)
    {
        int gridWidth = 11;
        int gridHeight = 7;

        int counter = 1;
        bool drawing = true;
        bool foundNext = false;

        lineRenderer.positionCount = mapMatrix.Cast<int>().Max();

        while (drawing)
        {
            Vector3 firstPoint = new Vector3(123123, 1231231, 1231231);
            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < 11; j++)
                {
                    if (mapMatrix[i, j] == counter)
                    {
                        firstPoint = new Vector3(j * (float)gridWidth / 11f - 5.5f, -i * (float)gridHeight / 7f + 3.5f, -0.5f);
                        foundNext = true;
                    }
                }
            }

            if (foundNext)
            {
                lineRenderer.SetPosition(counter - 1, firstPoint);
                counter++;
                foundNext = false;
            }
            else
            {
                drawing = false;
                break;
            }

        }
        if (bola == null)
            bola = GameObject.FindWithTag("Ball").GetComponent<BallClick>();
        if (!SingletonInt.Instance.isPlayer) {
            bola.moveEnemyBall(mapMatrix);
        }
    }
}
