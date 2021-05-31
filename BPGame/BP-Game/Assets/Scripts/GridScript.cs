using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GridScript : MonoBehaviour
{
    int height = 7;
    int width = 11;

    public Vector3[] grid;
    public FrogSpawn frogSpawn;



    void Start()
    {
        grid = new Vector3[height * width];
        Debug.Log(grid.Length);

        Vector2 startingPos = gameObject.transform.position;

        float limX = startingPos.x + width;
        float limY = startingPos.y - height;
        int counter = 0;

        for (float j = startingPos.y; j > limY; j--)
        {
            for (float i = startingPos.x; i <limX; i++)
            {

                grid[counter] = new Vector3(i, j,0);
                counter++;
                
            }
        }
       SingletonGrids.Instance.setGlobalGrid(grid);
        Invoke("triggerZValues", 0.2f);
    }
    void triggerZValues() {
        SingletonGrids.Instance.asignZValues();
    }


}
    
