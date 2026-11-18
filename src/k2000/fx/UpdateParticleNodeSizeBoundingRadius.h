// UpdateParticleNodeSizeBoundingRadius.h - the particle node's bounding radius from its emitter's particle size
// (original unit 0xe5c80-0xe5fb8, one function).
#pragma once

class CParticlesNodeFx;

// 0x000e5c80 UpdateParticleNodeSizeBoundingRadius: half the largest particle size the emitter can give (the multi size
// keys, else the size property's start / end size with their biases, else the PTank's constant size; 0 without any)
// into the node's +0x2c.
void UpdateParticleNodeSizeBoundingRadius(CParticlesNodeFx* node);
