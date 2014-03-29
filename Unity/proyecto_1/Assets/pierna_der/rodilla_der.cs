
/**
*  @file rodilla_der.cs
*  @brief PFC de Jorge Regidor - UAH  
* 
*  Imprime los movimientos en la rodilla derecha
* 
*  @author Jorge Regidor
*  @date 10/2013
*  @Version 1.0
*/


/// Importamos librerias
using UnityEngine;
using System.Collections;

/// Creamos la clase
public class rodilla_der : MonoBehaviour {

	
// ================================================================
// ===                         START                            ===
// ================================================================
	void Start () {
	
	} // final start
	
// ================================================================
// ===                         UPDATE                           ===
// ================================================================
	void Update () {
	
		/// Imprime los movimientos a la velocidad determinada
	transform.rotation = Quaternion.Slerp (transform.rotation, gui.qA , gui.speed * Time.deltaTime);
	} // final Update
} // Final clase
