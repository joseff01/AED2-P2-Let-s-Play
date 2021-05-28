using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

/**
 * @brief Class created to radomly spawn frogs
 * */
public class FrogSpawn : MonoBehaviour
{
    public GameObject ally; // Enemy
    public GameObject enemy; // Enemy
    public Vector3[] allyplacements; //Placements of all ally frogs
    public Vector3[] enemyplacements; //Placements of all enemy frogs

    public void allyPlacement(int num)
    {
        for (int i = 0; i< num; i++)
        {
            int randomNum = Random.Range(0, allyplacements.Length);
            Instantiate(ally, allyplacements[randomNum],Quaternion.identity);
            allyplacements = allyplacements.Except(new Vector3[] { allyplacements[randomNum]}).ToArray();

            int randomNum2 = Random.Range(0, enemyplacements.Length);
            Instantiate(enemy, enemyplacements[randomNum2], Quaternion.identity);
            enemyplacements = enemyplacements.Except(new Vector3[] { enemyplacements[randomNum2] }).ToArray();
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        allyPlacement(SingletonInt.Instance.value);
    }

}