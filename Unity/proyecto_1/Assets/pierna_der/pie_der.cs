
/**
*  @file pie_der.cs
*  @brief PFC de Jorge Regidor - UAH  
* 
*  Imprime los movimientos en el pie derecho
* 
*  @author Jorge Regidor
*  @date 10/2013
*  @Version 1.0
*/


/// Importamos librerias
using UnityEngine;
using System.Collections;

/// Creamos la clase
public class pie_der : MonoBehaviour {

// ================================================================
// ===                         START                            ===
// ================================================================
	void Start () {
	
	} // final start
	
// ================================================================
// ===                         UPDATE                           ===
// ================================================================
	void Update () {
		
	///	Imprimimos los movimientos a la velocidad determinada
	transform.rotation = Quaternion.Slerp (transform.rotation, gui.qB , gui.speed * Time.deltaTime);
	} // final Update
} //final clase
