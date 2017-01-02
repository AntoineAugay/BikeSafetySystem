//
// Created by Antoine on 02/12/2016.
//

#ifndef GPIO_MANAGER_H
#define GPIO_MANAGER_H

/*!
 * \file GPIO_manager.h
 * \brief GPIO manager of arduino Fio board
 * \author AUGAY Antoine
 * \version 0.1
 */

#include <arduino.h>



/*! \class GPIO_manager
   * \brief classe de gestion des clignotants
   *
   */
class GPIO_manager {
private:

public:

    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe GPIO_manager
     *
     *  \param nothing
     */
    GPIO_manager();

    /*!
     *  \brief set a pin as output
     *
     *  \param pin : pin number on the board
     *  \return nothing
     */
    void init_output_pin(int pin);

    /*!
     *  \brief set a pin as input
     *
     *  \param pin : pin number on the board
     *  \return nothing
     */
    void init_input_pin(int pin);

    /*!
     *  \brief set a pin
     *
     *  \param pin : pin number on the board
     *  \param state : 1 or 0
     *  \return nothing
     */
    void set_pin(int pin, bool state);

	/*!
	*  \brief Change a turn signal state
	*
	*  \param pin : pin number on the board
	*  \param state : 1 or 0 (0 : turn signal off)
	*  \return nothing
	*/
	bool read_pin(int pin);
};


#endif //GPIO_MANAGER_H
