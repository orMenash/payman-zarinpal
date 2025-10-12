import pytest

from zarinpal.gateway import ZarinPal


def test_gateway_initialization_defaults():
    gateway = ZarinPal(merchant_id="abcd-1234")
    assert gateway.merchant_id == "abcd-1234"
    assert gateway.version == 4
    assert gateway.sandbox is False
    assert "zarinpal.com" in str(gateway.base_url)


def test_gateway_invalid_merchant():
    with pytest.raises(ValueError):
        ZarinPal(merchant_id=None)


def test_gateway_custom_http_client(mocker):
    mock_http = mocker.Mock()
    gateway = ZarinPal("abcd", http_client=mock_http)
    assert gateway.client._http is mock_http
