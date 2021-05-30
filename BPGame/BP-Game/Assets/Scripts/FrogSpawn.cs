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

    public void allyPlacement(int num)
    {
        for (int i = 0; i< num; i++)
        {
            //  Placements of all ally frogs
            int randomNum = Random.Range(0, allyplacements.Length);
            //  Erases element from list
            Instantiate(ally, allyplacements[randomNum],Quaternion.identity);
            allyplacements = allyplacements.Except(new Vector3[] { allyplacements[randomNum]}).ToArray();

            //  Placements of all enemy frogs
            randomNum = Random.Range(0, enemyplacements.Length);
            //  Erases element from list
            Instantiate(enemy, enemyplacements[randomNum], Quaternion.identity);
            enemyplacements = enemyplacements.Except(new Vector3[] { enemyplacements[randomNum] }).ToArray();
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        allyPlacement(SingletonInt.Instance.value);
    }

}