import pytest

from zarinpal.methods.reverse_transaction import ReverseTransaction
from zarinpal.models import ReverseResponse


class DummyClient:
    async def post(self, url, body):
        return {"data": {"code": 100, "message": "OK"}}


@pytest.mark.asyncio
async def test_reverse_transaction_success():
    r = ReverseTransaction()
    r.client = DummyClient()
    result = await r.reverse({"authority": "A123"})
    assert isinstance(result, ReverseResponse)
    assert result.success
