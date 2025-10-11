import pytest

from zarinpal.methods.payment_initiator import PaymentInitiator
from zarinpal.models import PaymentRequest, PaymentResponse


class DummyClient:
    async def post(self, url, body):
        return {
            "data": {
                "code": 100,
                "message": "OK",
                "authority": "XYZ",
                "fee_type": "merchant",
                "fee": 0,
            }
        }


@pytest.mark.asyncio
async def test_initiate_payment_with_dict(mocker):
    inst = PaymentInitiator()
    inst.client = DummyClient()
    result = await inst.initiate_payment(
        {"amount": 1000, "description": "x", "callback_url": "https://a.com"}
    )
    assert isinstance(result, PaymentResponse)
    assert result.code == 100
