// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "OVR_platform.h"

#define OCULUS_APP_ID "2674439515908491"

int main()
{
    std::cout << "Hello World!\n"; 
	// Initialization call
	if (ovr_PlatformInitializeWindows(OCULUS_APP_ID) != ovrPlatformInitialize_Success)
	{
		// Exit.  Initialization failed which means either the oculus service
		// isn’t on the computer or the DLL is not valid.
		std::cout << "Invalid!!!\n";
	}
	else
	{
		std::cout << "Valid!!\n";
	}

	ovrID my_id = ovr_GetLoggedInUserID();
	//ovr_User_GetLoggedInUser()
	std::cout<< "My id:" << my_id << std::endl;

	//ovrRequest my_request = ovr_User_GetUserProof();
	//ovrRequest my_request = ovr_User_GetAccessToken();
	ovrRequest my_request = ovr_User_Get(my_id);
	// Poll for a response
	ovrMessage* message;
	while(true)
	while ((message = ovr_PopMessage()) != nullptr)
	{
		std::cout << "Uuh" << std::endl;

		switch (ovr_Message_GetType(message))
		{
		case ovrMessage_Entitlement_GetIsViewerEntitled:
			if (!ovr_Message_IsError(message))
			{
				// User is entitled.  Continue with normal game behaviour

			}
			else
			{
				// User is NOT entitled.  Exit
			}
			break;
		case ovrMessage_User_GetUserProof:
		//case ovrMessage_User_GetAccessToken:
			if (!ovr_Message_IsError(message))
			{
				// User is entitled.  Continue with normal game behaviour
				std::cout << "Got Proof!!" << std::endl;
				std::cout << message << std::endl;
				ovrUserProofHandle handle = ovr_Message_GetUserProof(message);
				std::cout << handle << std::endl;

				std::cout << ovr_UserProof_GetNonce(handle) << std::endl;
			}
			else
			{
				std::cout << "Errored!!" << std::endl;

				// User is NOT entitled.  Exit
			}
			break;
		case ovrMessage_User_GetAccessToken:
			if (!ovr_Message_IsError(message))
			{
				// User is entitled.  Continue with normal game behaviour
				std::cout << "Got token!!" << std::endl;
				std::cout << message << std::endl;

				std::cout << ovr_Message_GetString(message) << std::endl;
			}
			else
			{
				std::cout << "Errored!!" << std::endl;

				// User is NOT entitled.  Exit
			}
			break;
		case ovrMessage_User_Get:
			if (!ovr_Message_IsError(message))
			{
				// User is entitled.  Continue with normal game behaviour
				std::cout << "Got userr!!" << std::endl;
				std::cout << message << std::endl;
				ovrUserHandle handle = ovr_Message_GetUser(message);

				ovrID idd = ovr_User_GetID(handle);

				std::cout << "GetPresence: " << ovr_User_GetPresence(handle) << std::endl << std::endl;
				std::cout << "GetPresenceStatus: " << ovr_User_GetPresenceStatus(handle) << std::endl << std::endl;
				std::cout << "Id: " << idd << std::endl;
				std::cout << "ImageURL: " << ovr_User_GetImageUrl(handle) << std::endl << std::endl;
				//std::cout << "InviteToken: " << ovr_User_GetInviteToken(handle) << std::endl;
				std::cout << "OculusID: " << ovr_User_GetOculusID(handle) << std::endl << std::endl;
				std::cout << "SmallImageUrl: " << ovr_User_GetSmallImageUrl(handle) << std::endl << std::endl;

				std::cout << "endo" << std::endl;
			}
			else
			{
				std::cout << "Errored!!" << std::endl;

				// User is NOT entitled.  Exit
			}
		default:
			break;
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
