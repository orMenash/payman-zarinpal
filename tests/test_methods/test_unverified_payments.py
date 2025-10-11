import pytest

from zarinpal.methods.get_unverified_payments import GetUnverifiedPayments
from zarinpal.models import UnverifiedPayments


class DummyClient:
    async def post(self, url, body=None):
        return {"data": {"code": 100, "message": "ok", "authorities": []}}


@pytest.mark.asyncio
async def test_get_unverified_payments():
    g = GetUnverifiedPayments()
    g.client = DummyClient()
    result = await g.get_unverified_payments()
    assert isinstance(result, UnverifiedPayments)
    assert result.success
