//
// Created by Antoine on 02/12/2016.
//

#ifndef FRAME_MANAGER_H
#define FRAME_MANAGER_H


/*!
 * \file Frame_manager.h
 * \brief Frame manager
 * \author AUGAY Antoine
 * \version 0.1
 */

#include <arduino.h>
#include "String_queue.h"

/*! \class Frame_manager
   * \brief
   *
   */
class Frame_manager {
private:

   String_queue messages; /*!< queue of message extract from frames received*/

public:


    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe Frame_manager
     *
     *  \param nothing
     */
    Frame_manager();

    /*!
     *  \brief collect data from the frame
     *
     *  Extract information in frame and put all message in the queue messages
     *
     *  \param frame, frame structure : header(1 octet) and data (n octets)
     *  \return nothing
     */
    void parse(char* frame, int size);

	/*!
	*  \brief build a frame form the command
	*
	*  \param command, command a envoyé
	*  \return nothing
	*/
	unsigned char* builder(String command);

    /*!
     *  \brief get the oldest message received
     *
     *
     *  \param nothing
     *  \return return a empty string if the queue is empty
     *          if not the last message added in the list
     */
    String pop_message();

};


#endif //FRAME_MANAGER_H
