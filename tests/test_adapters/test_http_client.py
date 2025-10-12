import pytest
import pytest_asyncio

from zarinpal.adapters.http_client import ZarinpalHttpClient
from zarinpal.adapters.error_mapper import ErrorMapper
from zarinpal.exception import ZarinPalGatewayException


class DummyHTTP:
    async def request(self, method, url, json_data=None):
        return {"data": {"status": "ok"}}


@pytest_asyncio.fixture
async def client():
    return ZarinpalHttpClient(
        merchant_id="123",
        base_url="https://sandbox.zarinpal.com",
        http_client=DummyHTTP(),
        error_mapper=ErrorMapper({}, ZarinPalGatewayException),
    )


@pytest.mark.asyncio
async def test_post_includes_merchant_id(client):
    result = await client.post("/request.json", {"amount": 1000})
    assert "data" in result
