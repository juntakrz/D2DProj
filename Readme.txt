ANIMATION METHOD REFERENCE

"AlphaScaleMove_ToBase"
(transitions opacity, size and pos from given variables to base variables)

"AlphaScaleMove_FromBase"
(transitions opacity, size and pos from base variables to given variables)

Animation parameters (Vector8f):
[0] length (frames)
[1] delay (frames)
[2] alpha (0.0f - 1.0f)
[3] scale (e.g. 1.35f = 135%)
[4] horizontal displacement (pixels)
[5] vertical displacement (pixels)
[6-7] UNUSED

Animation dynamic data (Vector8f):
[0] alpha increment per frame
[1] width increment per frame (pixels)
[2] height increment per frame (pixels)
[3] horizontal increment per frame (pixels)
[4] vertical increment per frame (pixels)
[5] processed hor displacement (pixels)
[6] processed ver displacement (pixels)
[7] UNUSED

"Scale_ToBase"
(transitions size from given variables to base variables)

"Scale_FromBase"
(transitions size from base variables to given variables)

Animation parameters (Vector8f):
[0] length (frames)
[1] delay (frames)
[2] scale (e.g. 1.35f = 135%)
[3-7] UNUSED

Animation dynamic data (Vector8f):
[0] width increment per frame (pixels)
[1] height increment per frame (pixels)
[2-7] UNUSED