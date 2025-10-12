import pytest

from zarinpal.adapters.error_mapper import ErrorMapper
from zarinpal.exception import ZarinPalGatewayException, ValidationException


def test_error_mapper_success_case():
    mapper = ErrorMapper({-9: ValidationException}, ZarinPalGatewayException)
    response = {"data": {"ok": True}}
    mapper.map(response)  # should not raise


def test_error_mapper_empty_response():
    mapper = ErrorMapper({}, ZarinPalGatewayException)
    with pytest.raises(ZarinPalGatewayException):
        mapper.map({})


def test_error_mapper_known_error():
    mapper = ErrorMapper({-9: ValidationException}, ZarinPalGatewayException)
    response = {"errors": {"code": -9, "message": "invalid"}}
    with pytest.raises(ValidationException):
        mapper.map(response)
