using UnityEngine;
public class ChangeInt : MonoBehaviour
{
    public void changeSingleInt(int num) {
        SingletonInt.Instance.value = num;
    }
}
