void CPlayerComponent::UpdateCamera(float frameTime)
{
	Ang3 ypr = CCamera::CreateAnglesYPR(Matrix33(m_lookOrientation));

	// Ignore z-axis rotation, that's set by CPlayerAnimations
	// ypr.x = 0;

	// Start with changing view rotation to the requested mouse look orientation
	Matrix34 localTransform = IDENTITY;
	Vec3 cameraDirection = CCamera::CreateViewdir(ypr);
	localTransform.SetRotation33(CCamera::CreateOrientationYPR(ypr));

	// Offset the player along the forward axis (normally back)
	// Also offset upwards
	const float viewOffsetForward = -1.5f;
	const float viewOffsetUp = 2.5f;
	cameraDirection = (cameraDirection * 3) + Vec3(0, -0.15f, 0);
	localTransform.SetTranslation(cameraDirection * -2.f);

	m_pCameraComponent->SetTransformMatrix(localTransform);
	m_pAudioListenerComponent->SetOffset(localTransform.GetTranslation());
}
