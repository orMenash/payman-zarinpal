import pytest

from zarinpal.methods.verify_payment import VerifyPayment
from zarinpal.models import VerifyResponse


class DummyClient:
    async def post(self, url, body):
        return {"data": {"code": 100, "ref_id": 12345}}


@pytest.mark.asyncio
async def test_verify_payment_success():
    v = VerifyPayment()
    v.client = DummyClient()
    result = await v.verify_payment({"amount": 1000, "authority": "A123"})
    assert isinstance(result, VerifyResponse)
    assert result.success
