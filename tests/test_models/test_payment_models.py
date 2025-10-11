import pytest
from pydantic import ValidationError

from zarinpal.models import PaymentRequest, Wage, PaymentMetadata


def test_valid_payment_request():
    req = PaymentRequest(
        amount=1000,
        description="Test",
        callback_url="https://example.com/callback",
    )
    assert req.amount == 1000


def test_invalid_currency():
    with pytest.raises(ValidationError):
        PaymentRequest(
            amount=1000, description="x", callback_url="https://a.com", currency="USD"
        )


def test_invalid_wages_length():
    wages = [Wage(iban="IR123456789012345678901234", amount=1, description="x")] * 10
    with pytest.raises(ValidationError):
        PaymentRequest(
            amount=1000, description="x", callback_url="https://a.com", wages=wages
        )


def test_payment_metadata_format():
    meta = PaymentMetadata(email="user@example.com")
    assert meta.email == "user@example.com"
