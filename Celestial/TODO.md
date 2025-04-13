### Todo
	Figure out how to have several "cameras" to superimpose a UI over content
	
	Make textblock based ui
		(fontsize is equal to line size? if so we can easily place things vertically)

	MILESTONE: Figure out virtual space (2d orthographic projection)
		World origin
		Camera origin
		Camera width, height (bidimensionnal scaling, probably wont be necessary and w/h will correspond to the screen)

	New texture: circle (color, radius, segments?)

	Implement ECS to gameobject
	Create class compoment with like the update function (just declare signature) and thats all
	Create class for each special behavior and have an update function (use override to hint user) with the desired behavior
	
	MILESTONE New game object component: PointMass
		position, velocity
		calculate gravity component (for others)
		calculate gravity (check all other game objects that have pointmass component, get their gravity component, apply acceleration (from sum of all components) to self)
