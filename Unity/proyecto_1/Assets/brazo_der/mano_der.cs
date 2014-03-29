/**
*  @file mano_der.cs
*  @brief PFC de Jorge Regidor - UAH  
* 
*  Imprime los movimientos en la mano derecha
* 
*  @author Jorge Regidor
*  @date 10/2013
*  @Version 1.0
*/


/// Importamos librerias
using UnityEngine;
using System.Collections;
 
// creamos la clase
public class mano_der : MonoBehaviour {

// ================================================================
// ===                         START                            ===
// ================================================================
	void Start () {
	
	} // final start
	
// ================================================================
// ===                         UPDATE                           ===
// ================================================================
	void Update () {
	/// Imprimimos los movimientos a la velocidad determinada
	transform.rotation = Quaternion.Slerp (transform.rotation, gui.q2 , gui.speed * Time.deltaTime);
	} // final update
} // final clase
