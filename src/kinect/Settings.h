#pragma once


namespace kinect {


	struct Settings {

		friend class Kinect;


		static void  setAngle(Kinect&, int);
		static float getAngle(Kinect&);

		static void setCutoffDistance(Kinect&, int);
		static int  getCutoffDistance(Kinect&);

		//static void  setUseMirroring(Kinect&, bool);
		//static bool  getUseMirroring(Kinect&);

		//static void  setUseBackgroundSubtraction(Kinect&, bool);
		//static bool  getUseBackgroundSubtraction(Kinect&);


		//bool  use_mirroring{ false };
		//bool  use_background_subtraction{ false };

		// maybe make static or move
		

	};

}
