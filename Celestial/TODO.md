### Todo
	Figure out how to have several "cameras" to superimpose a UI over content
	-- DONE WITH GROUPS --
	
	MILESTONE: Figure out virtual space (2d orthographic projection)
		World origin
		Camera origin
		Camera width, height (bidimensionnal scaling, probably wont be necessary and w/h will correspond to the screen)
		
		Is game directly responsible for the camera?
		I need a way to tell the texture component whether or not it is relative to a camera
			if so, adapt scale and position (dont render at all if out of screen)
			in fact we will always have a camera, but let us have several at once (camera array stored in game)
				simple example: 1 camera for world, 1 camera for UI
		later find a way to rotate the camera to different axes ( (x,y) -> (x,z), ...)

	New texture: circle (color, radius, segments?)
	 
	Implement ECS to gameobject
	Create class compoment with like the update function (just declare signature) and thats all
	Create class for each special behavior and have an update function (use override to hint user) with the desired behavior
	-- ECS DONE --
	
	MILESTONE New game object component: PointMass
		position, velocity
			for position, regular int (32) wont be enough. regular long will be too much. use uint_least32_t ?
			for speed, whatever: fastest(?) object in the solar system is mercury, at ~50km/s (much less than max int32, 2e9)
		calculate gravity component (for others)
			make magnitude analysis to decide if we need to use double or long double
		calculate gravity (check all other game objects that have pointmass component, get their gravity component, apply acceleration (from sum of all components) to self)
		
	Make textblock based ui
		(fontsize is equal to line size? if so we can easily place things vertically)
