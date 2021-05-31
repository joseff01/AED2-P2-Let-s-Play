using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

/**
 * @brief Class that radomly spawns enemy and ally frogs
 * */
public class FrogSpawn : MonoBehaviour
{
    public GameObject ally; // Ally frogs
    public GameObject enemy; // Enemy frog
    public Vector3[] allyplacements; // Placements of all ally frogs
    public Vector3[] enemyplacements; // Placements of all enemy frogs
    public Vector2[] frogPlacements;

    public void allyPlacement(int num)
    {
        int counter = 0;
        frogPlacements = new Vector2[num*2];
        for (int i = 0; i< num; i++)
        {
            //  Placements of all ally frogs
            int randomNum = Random.Range(0, allyplacements.Length);
            //  Erases element from list
            Instantiate(ally, allyplacements[randomNum],Quaternion.identity);
            frogPlacements[counter] = allyplacements[randomNum];
            allyplacements = allyplacements.Except(new Vector3[] { allyplacements[randomNum]}).ToArray();
            counter++;

            //  Placements of all enemy frogs
            randomNum = Random.Range(0, enemyplacements.Length);
            //  Erases element from list
            Instantiate(enemy, enemyplacements[randomNum], Quaternion.identity);
            frogPlacements[counter] = enemyplacements[randomNum];
            enemyplacements = enemyplacements.Except(new Vector3[] { enemyplacements[randomNum] }).ToArray();
            counter++;
        }
        SingletonGrids.Instance.setGlobalFrogGrid(frogPlacements);
    }

    // Start is called before the first frame update
    void Start()
    {
        allyPlacement(SingletonInt.Instance.value);
    }

}