

/**
*  @file rodilla_izq.cs
*  @brief PFC de Jorge Regidor - UAH  
* 
*  Imprime los movimientos en la rodilla izquierda
* 
*  @author Jorge Regidor
*  @date 10/2013
*  @Version 1.0
*/


/// Importamos librerias
using UnityEngine;
using System.Collections;

/// Creamos la clase
public class rodilla_izq : MonoBehaviour {
	
// ================================================================
// ===                         START                            ===
// ================================================================
	void Start () {
	
	} // final start
	
// ================================================================
// ===                         UPDATE                           ===
// ================================================================
	void Update () {
	
		/// Imprime los valores a la velocidad determinada
		transform.rotation = Quaternion.Slerp (transform.rotation, gui.q7 , gui.speed * Time.deltaTime);
	} // final update
} // final clase
