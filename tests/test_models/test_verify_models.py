from zarinpal.models import VerifyResponse
from zarinpal.enums import Status


def test_verify_response_properties():
    vr = VerifyResponse(code=Status.SUCCESS, ref_id=10)
    assert vr.success
    vr2 = VerifyResponse(code=Status.ALREADY_VERIFIED)
    assert vr2.already_verified
