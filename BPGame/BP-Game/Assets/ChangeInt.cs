using UnityEngine;

public class ChangeInt : MonoBehaviour
{
    public void changeSingleInt(int num) {
        GlobalVariable.Instance.value = num;
        Debug.Log(num);
    }
}
