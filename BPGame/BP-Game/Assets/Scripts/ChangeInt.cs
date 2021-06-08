using UnityEngine;
public class ChangeInt : MonoBehaviour
{
    public void changeSingleInt(int num) {
        SingletonInt.Instance.value = num;
    }
    public void changeGoalInt(int num)
        {
            SingletonInt.Instance.goalValue = num;
        }
}
